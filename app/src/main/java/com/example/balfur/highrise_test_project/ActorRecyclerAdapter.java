package com.example.balfur.highrise_test_project;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.example.balfur.highrise_test_project.POJOs.Actor;
import com.squareup.picasso.Picasso;

import java.util.List;

public class ActorRecyclerAdapter extends RecyclerView.Adapter<ActorRecyclerAdapter.ViewHolder> {

    private List<Actor> mItems;
    private Context ctx;

    public ActorRecyclerAdapter(List<Actor> items) {
        mItems = items;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        this.ctx = parent.getContext();
        return new ViewHolder(LayoutInflater.from(parent.getContext())
                .inflate(R.layout.actor_adapter_item, parent, false));
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        holder.setData(mItems.get(position));
    }

    @Override
    public int getItemCount() {
        return mItems.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {

        private ImageView imageView;
        private TextView nameTextView;
        private TextView ageTextView;
        public Actor actor;

        public ViewHolder(View itemView) {
            super(itemView);
            imageView = itemView.findViewById(R.id.actor_image);
            nameTextView = itemView.findViewById(R.id.actor_name);
            ageTextView = itemView.findViewById(R.id.actor_age);

            boolean isImageFitToScreen;

            imageView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    imageView.setScaleType(ImageView.ScaleType.FIT_XY);
                }
            });
        }

        public void setData(Actor actor) {
            this.actor = actor;
            try {
                Picasso.with(ctx).load(actor.getImageUrl()).into(imageView);
                Log.e("Actor Adapter", "Loading image for actor " + actor.getName());
            } catch (IllegalArgumentException e){
                Log.e("Actor Adapter", "No actor image found, showing anonymous");
                Picasso.with(ctx).load("http://www.knowmuhammad.org/img/noavatarn.png").into(imageView);
            }
            nameTextView.setText(actor.getName());
            ageTextView.setText(actor.getAge() + " years old");
        }
    }

}
